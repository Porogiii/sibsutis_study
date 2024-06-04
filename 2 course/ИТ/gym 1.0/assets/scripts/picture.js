const firstImg = document.querySelector('.change__first-img');
const secondImg = document.querySelector('.change__second-img');

firstImg.addEventListener('mouseenter', () => {
  firstImg.classList.add('enlarge');
  secondImg.style.zIndex = '-1';
});

firstImg.addEventListener('mouseleave', () => {
  firstImg.classList.remove('enlarge');
  secondImg.style.zIndex = '0';
});

secondImg.addEventListener('mouseenter', () => {
  secondImg.classList.add('enlarge');
  firstImg.style.zIndex = '-1';
});

secondImg.addEventListener('mouseleave', () => {
  secondImg.classList.remove('enlarge');
  firstImg.style.zIndex = '0';
});



const FirstImg = document.querySelector('.premium__first-img');
const SecondImg = document.querySelector('.premium__second-img');

function handleMouseEnter(targetImg, otherImg) {
  targetImg.classList.add('enlarge');
  otherImg.style.zIndex = '-1';
}

function handleMouseLeave(targetImg, otherImg) {
  targetImg.classList.remove('enlarge');
  otherImg.style.zIndex = '0';
}

FirstImg.addEventListener('mouseenter', () => {
  handleMouseEnter(FirstImg, SecondImg);
});

FirstImg.addEventListener('mouseleave', () => {
  handleMouseLeave(FirstImg, SecondImg);
});

SecondImg.addEventListener('mouseenter', () => {
  handleMouseEnter(SecondImg, FirstImg);
});

SecondImg.addEventListener('mouseleave', () => {
  handleMouseLeave(SecondImg, FirstImg);
});
