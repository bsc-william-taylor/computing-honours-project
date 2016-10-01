
const { get, post } = compute;

exports.post = function(domain, path, port, body, callback) {
    post(domain, path, port, callback, JSON.stringify(body));
};

exports.get = function(domain, path, port, callback) {
    get(domain, path, port, callback);
}