import optparse 
from flask import Flask, render_template, request
from flask_cors import CORS

app = Flask(__name__)
CORS(app)
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
@app.route('/',methods=('GET','POST'))
def index():
    if request.method == "POST":
        data = request.get_json() #recieve request
        if data['action'] == 1: #  write to the LED data object
            LED_data.set_values(data)
            result = "*{:02X}{:02X}{:02X}".format(LED_data.R, LED_data.G, LED_data.B)
            with open("result.txt","w") as file1:
                file1.write(result)

        elif int(data['action']) == 0: # return the values for LED data as hex code
            result = "*{:02X}{:02X}{:02X}".format(LED_data.R, LED_data.G, LED_data.B)
            
            return result

    return render_template('index.html')

@app.route('/request',methods=['GET'])
def req():
    file1 = open("result.txt","r")
    result = file1.readlines()[0]
    file1.close()
    return result

if __name__ == '__main__':
    default_port = "80"
    default_host = "0.0.0.0"
    parser = optparse.OptionParser()
    parser.add_option("-H", "--host",
                      help=f"Hostname of Flask app {default_host}.",
                      default=default_host)

    parser.add_option("-P", "--port",
                      help=f"Port for Flask app {default_port}.",
                      default=default_port)

    parser.add_option("-d", "--debug",
                      action="store_true", dest="debug",
                      help=optparse.SUPPRESS_HELP)

    options, _ = parser.parse_args()

    app.run(
        #debug=options.debug,
        debug=True,
        host=options.host,
        port=int(options.port)
    )