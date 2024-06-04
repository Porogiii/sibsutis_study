function toggleWindow() {
  const messageWindow = document.querySelector(".modal__container");
  const buttons = document.querySelectorAll(".btn-modal");
  buttons.forEach((el) => {
    el.addEventListener("click", (e) => {
      messageWindow.classList.add("active");
    });
  });
  messageWindow.addEventListener("click", (e) => {
    console.log(e.target.classList.contains("modal__container"));
    if (e.target.classList.contains("modal__container")) {
      messageWindow.classList.remove("active");
    }
  });
}

function sendData() {
  const btn = document.querySelector(".modal__btn");
  console.log(btn);
  const messageWindow = document.querySelector(".modal__container");

  btn.addEventListener("click", () => {
    console.log(4323);
    btn.classList.add("sending");
    fetch("https://jsonplaceholder.typicode.com/todos/1")
      .then((response) => response.json())
      .then((json) => {
        alert("Заявка отправлена");
        btn.classList.remove("sending");
        messageWindow.classList.remove("active");

        console.log(json);
      });
  });
}

sendData();
toggleWindow();
