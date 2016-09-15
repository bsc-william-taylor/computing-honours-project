
const bodyParser = require('body-parser');
const express = require('express');
const cors = require('cors');
const fs = require('fs');
const app = express();

app.use(bodyParser.json());
app.use(cors());

app.get('/shapes', (req, res) => {
  const contents = JSON.parse(fs.readFileSync("shapes.json", "utf8"));
  res.json(contents);
});

app.get('/kernels', (req, res) => {
  res.json({'text': fs.readFileSync("kernels.cl", "utf8")});
});

app.post('/shapes', (req, res) => {
  fs.writeFileSync('shapes.json', JSON.stringify(req.body));
  res.json({"msg": "done"})
});

app.post('/kernels', (req, res) => {
  fs.writeFileSync('kernels.cl', JSON.stringify(req.body));
  res.json({"msg": "done"})
});

const server = app.listen(3010, () => {
  const host = server.address().address;
  const port = server.address().port;

  console.log(`Listening at http://${host}:${port}`);
});