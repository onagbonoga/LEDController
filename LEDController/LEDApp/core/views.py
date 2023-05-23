from flask import Flask, render_template, request, Blueprint

core_app = Blueprint('Core', __name__)

class LED():
    def __init__(self):
        self.R = 50
        self.G = 50
        self.B = 50
    def set_values(self,data):
        self.R = int(data['R'])
        self.G = int(data['G'])
        self.B = int(data['B'])

LED_data = LED()
@core_app.route('/',methods=('GET','POST'))
def index():
    if request.method == "POST":
        data = request.get_json() #recieve request
        if data['action'] == 1: #  write to the LED data object
            LED_data.set_values(data)

        elif int(data['action']) == 0: # return the values for LED data as hex code
            result = "*{:02X}{:02X}{:02X}".format(LED_data.R, LED_data.G, LED_data.B)
            
            return result

    return render_template('index.html')
