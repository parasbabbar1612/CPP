const randcolor=()=>{
    const r=Math.floor(Math.random()*255);
    const g=Math.floor(Math.random()*255);
    const b=Math.floor(Math.random()*255);
    alert('Color changed...Press ok to see change');
    return `rgb(${r},${g},${b})`;
}
const btn=document.querySelector('#t1');
btn.addEventListener('click',function(){
    const str=randcolor();
    document.body.style.backgroundColor=str;
    const heading=document.querySelector('h1');
    heading.innerText=str;
});