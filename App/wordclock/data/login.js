const form = document.querySelector('form');
const btn = document.querySelector('button');
form.addEventListener('submit', e => {
  e.preventDefault();
  form.classList.add('pending');
  btn.innerHTML = '<span>.</span><span>.</span><span>.</span>';

  const password = document.querySelector('#password').value;
  const ssid = document.querySelector('#ssid').value;
  const xhttp = new XMLHttpRequest();

  const jsonData = {
    ssid,
    password,
  };
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      btn.innerHTML = `<span style="font-size: 18px">${xhttp.responseText}</span>`;
    }
  };
  const url = `http://192.168.4.54/login`;
  xhttp.open('POST', url, true);
  xhttp.send(JSON.stringify(jsonData));
});
