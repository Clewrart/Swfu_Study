document.getElementById('loginForm').onsubmit = function(event) {
    event.preventDefault();

    var form = event.target;
    var formData = new FormData(form);

    fetch(form.action, {
            method: form.method,
            body: formData,
        }).then(response => response.json())
        .then(data => {
            if (data.success) {

                window.location.href = data.redirect_url;
            } else {

                alert(data.message);
            }
        }).catch(error => console.error('Error:', error));
};