// WORDLE.SYS — servidor local
// Usa apenas módulos nativos do Node.js (sem dependências)
// Rodar: node server.js

const http = require('http');
const fs   = require('fs');
const path = require('path');
const url  = require('url');

const PORT   = 8080;
const ROOT   = __dirname;
const SCORES = path.join(ROOT, 'scores.txt');

// ── Tipos MIME ───────────────────────────────────────────
const MIME = {
    '.html': 'text/html; charset=utf-8',
    '.js':   'application/javascript; charset=utf-8',
    '.css':  'text/css; charset=utf-8',
    '.txt':  'text/plain; charset=utf-8',
    '.ico':  'image/x-icon',
    '.png':  'image/png',
};

// ── Helpers ───────────────────────────────────────────────
function json(res, data, status = 200) {
    res.writeHead(status, {
        'Content-Type': 'application/json; charset=utf-8',
        'Access-Control-Allow-Origin': '*',
    });
    res.end(JSON.stringify(data));
}

function parseScores() {
    try {
        const raw = fs.readFileSync(SCORES, 'utf8');
        return raw
            .split('\n')
            .map(l => l.trim())
            .filter(Boolean)
            .map(line => {
                const parts = line.split(/\s+/);
                if (parts.length < 3) return null;
                const [name, word, attempts, ts] = parts;
                return {
                    name:     name,
                    word:     word,
                    attempts: parseInt(attempts, 10) || 0,
                    ts:       parseInt(ts, 10)       || 0,
                };
            })
            .filter(Boolean);
    } catch {
        return [];
    }
}

// ── Servidor ─────────────────────────────────────────────
const server = http.createServer((req, res) => {
    const { pathname } = url.parse(req.url);

    // CORS preflight
    if (req.method === 'OPTIONS') {
        res.writeHead(204, { 'Access-Control-Allow-Origin': '*', 'Access-Control-Allow-Methods': 'GET,POST', 'Access-Control-Allow-Headers': 'Content-Type' });
        res.end();
        return;
    }

    // ── GET /api/scores ───────────────────────────────────
    if (req.method === 'GET' && pathname === '/api/scores') {
        const scores = parseScores();
        // Ordena: menos tentativas primeiro, empate = mais recente primeiro
        scores.sort((a, b) => a.attempts - b.attempts || b.ts - a.ts);
        json(res, scores);
        return;
    }

    // ── POST /api/scores ──────────────────────────────────
    if (req.method === 'POST' && pathname === '/api/scores') {
        let body = '';
        req.on('data', chunk => { body += chunk; if (body.length > 1024) req.destroy(); });
        req.on('end', () => {
            try {
                const { name, word, attempts, ts } = JSON.parse(body);
                // Sanitiza campos (mesmo formato do main.c)
                const safeName = String(name || 'ANON').replace(/\s+/g, '_').slice(0, 20);
                const safeWord = String(word || '').toUpperCase().replace(/[^A-ZÁÉÍÓÚÂÊÔÃÕÇ]/gi, '').slice(0, 5);
                const safeAtt  = Math.max(1, Math.min(6, parseInt(attempts, 10) || 1));
                const safeTs   = parseInt(ts, 10) || Math.floor(Date.now() / 1000);
                const line     = `${safeName} ${safeWord} ${safeAtt} ${safeTs}\n`;
                fs.appendFileSync(SCORES, line, 'utf8');
                json(res, { ok: true });
            } catch (e) {
                json(res, { ok: false, error: 'invalid body' }, 400);
            }
        });
        return;
    }

    // ── Arquivos estáticos ────────────────────────────────
    // Previne path traversal
    const safe    = path.normalize(pathname).replace(/^(\.\.[/\\])+/, '');
    let   filePath = path.join(ROOT, safe === '/' ? 'index.html' : safe);

    try {
        if (fs.statSync(filePath).isDirectory()) {
            filePath = path.join(filePath, 'index.html');
        }
        const data    = fs.readFileSync(filePath);
        const ext     = path.extname(filePath).toLowerCase();
        const ctype   = MIME[ext] || 'application/octet-stream';
        res.writeHead(200, {
            'Content-Type': ctype,
            'Access-Control-Allow-Origin': '*',
            'Cache-Control': ext === '.txt' ? 'no-cache' : 'public, max-age=60',
        });
        res.end(data);
    } catch {
        res.writeHead(404); res.end('404 Not Found');
    }
});

server.listen(PORT, '127.0.0.1', () => {
    const line = `─`.repeat(42);
    console.log(`\n  ┌${line}┐`);
    console.log(`  │  WORDLE.SYS  ▶  http://localhost:${PORT}              │`);
    console.log(`  │  scores salvo em: scores.txt               │`);
    console.log(`  └${line}┘\n`);
    console.log('  Pressione Ctrl+C para encerrar.\n');
});
