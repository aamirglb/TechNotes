function processForm(e) {
    if(e.preventDefault)
        e.preventDefault();

    console.log("Intercept form submit");
    console.log(e)
    return false;
}

var form = document.getElementById('my-form');
console.log(form)
 if(form.attachEvent) {
     form.attachEvent("submit", processForm);
 } else {
     form.addEventListener("submit", processForm);
 }

console.log("javascript")