// Static server with cross-origin isolation headers (needed for SharedArrayBuffer).
const http = require('http'), fs = require('fs'), path = require('path');
const root = path.resolve(process.argv[2] || 'web'), port = +(process.env.PORT || process.argv[3] || 8790);
const types = { '.html': 'text/html', '.js': 'text/javascript', '.wasm': 'application/wasm', '.data': 'application/octet-stream', '.ogg': 'audio/ogg', '.json': 'application/json' };
http.createServer((req, res) => {
  const u = decodeURIComponent(req.url.split('?')[0]);
  let f = path.join(root, u.endsWith('/') ? u + 'index.html' : u);
  if (!f.startsWith(root)) { res.writeHead(403); return res.end(); }
  fs.stat(f, (err, st) => {
    if (err || !st.isFile()) { res.writeHead(404); return res.end('not found'); }
    res.writeHead(200, { 'Content-Type': types[path.extname(f)] || 'application/octet-stream', 'Content-Length': st.size,
      'Cross-Origin-Opener-Policy': 'same-origin', 'Cross-Origin-Embedder-Policy': 'require-corp', 'Cache-Control': 'no-cache' });
    fs.createReadStream(f).pipe(res);
  });
}).listen(port, () => console.log('serving', root, 'on', port));
