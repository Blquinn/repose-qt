from time import sleep

from flask import Flask, request, Response
from werkzeug.routing import Rule

app = Flask(__name__)
app.url_map.add(Rule('/', endpoint='index'))


@app.endpoint('index')
def echo():
    code = int(request.headers.get('x-response-code', 200))
    timeout = float(request.headers.get('x-sleep', 0.0))
    if timeout:
        sleep(timeout)
   
    headers = dict(request.headers.items())
    headers['X-Request-Path'] = request.path
    headers['X-Request-Query'] = request.query_string
    headers['X-Request-Method'] = request.method

    return Response(response=request.get_data(),
                    status=code,
                    headers=headers,
                    mimetype=request.mimetype,
                    content_type=request.content_type,
                    direct_passthrough=True)
