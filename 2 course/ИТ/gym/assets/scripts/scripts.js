function sliderHandler() {
  const slidesContainer = document.querySelectorAll(".slider__container");
  console.log(slidesContainer);
  slidesContainer.forEach((el) => {
    console.log(el);
    const sliderOverflow = el.querySelector(".slider__overflow");
    const buttonsArray = el.querySelectorAll(".slider__button-item");
    const interval = setInterval(() => {
      console.log(counter);
      if (counter === 3) counter = -1;
      counter++;
      buttonsArray.forEach((e) => {
        e.classList.remove("active");
      });
      buttonsArray[counter].classList.add("active");
      sliderOverflow.style.left = `-${counter}00%`;
    }, 3000);
    buttonsArray.forEach((el, index) => {
      el.addEventListener("click", () => {
        clearInterval(interval);
        buttonsArray.forEach((e) => {
          e.classList.remove("active");
        });
        el.classList.add("active");
        sliderOverflow.style.left = `-${index}00%`;
      });
    });
    let counter = 0;
  });
}

sliderHandler();
