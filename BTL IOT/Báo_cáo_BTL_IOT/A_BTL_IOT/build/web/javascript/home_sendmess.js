/* 
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/JSP_Servlet/JavaScript.js to edit this template
 */

//Xu li khi nhan nut bat tat
document.getElementById("onButtonquat").addEventListener("click", function () {
    //sendCommand("a");
    sendRequest("a");
});
document.getElementById("offButtonquat").addEventListener("click", function () {
    //sendCommand("b");
    sendRequest("b");
});
document.getElementById("onButton").addEventListener("click", function () {
    //sendCommand("c");
    sendRequest("c");
});
document.getElementById("offButton").addEventListener("click", function () {
    //sendCommand("d");
    sendRequest("d");
});
function sendCommand(command) {
    var xhr = new XMLHttpRequest();
    xhr.open("POST", "/A_BTL_IOT2/send", true);
    xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xhr.onreadystatechange = function () {
        if (xhr.readyState === 4 && xhr.status === 200) {
            // Xử lý phản hồi từ servlet
            console.log("Command sent successfully.");
        }
    };
    xhr.send("command=" + command);
}

function sendRequest(action) {
    $.ajax({
        type: "POST",  
        url: "/A_BTL_IOT2/send", 
        data: { command: action },
        success: function (data) {
            // Handle the response from the servlet if needed.
        },
        error: function (error) {
            // Handle errors if the request fails.
        }
    });
}


