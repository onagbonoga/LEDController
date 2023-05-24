var data = {
    action:1,//1 for write and 0 for read
    R:50,
    G:50,
    B:50
};
var R = document.getElementById("R");
var G = document.getElementById("G");
var B = document.getElementById("B");

// Update the current slider value (each time you drag the slider handle)

R.oninput = function() {
    data.R = this.value;
    updateValues();
}
G.oninput = function() {
    data.G = this.value;
    updateValues();
}
B.oninput = function() {
    data.B = this.value;
    updateValues();
}

//var url = "http://127.0.0.1:5000/";
//var url = "http://ledcontrollerapp.eba-9ctbsim3.us-east-1.elasticbeanstalk.com/";
var url = "http://23.22.100.108/"
function updateValues(){
    fetch(url,{
        method: 'POST',
        headers: {'Content-Type': 'application/json'},
        body: JSON.stringify(data)
    })
}

function requestData(){ 
    var data = {action:0};
    fetch(url,{
        method: 'POST',
        headers: {'Content-Type': 'application/json'},
        body: JSON.stringify(data)
    })
    .then(response => response.text())
    .then(result => {
      console.log(result);
    })
}