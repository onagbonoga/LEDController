from flask import Flask, render_template, request

app = Flask(__name__)

# register blue print
from LEDApp.core.views import core_app
app.register_blueprint(core_app)

