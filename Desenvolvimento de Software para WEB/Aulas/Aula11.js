const calcular = (num1,num2) => num1 + num2;

console.log(calcular(2,2))


function calcular_soma(num1, num2, callback){
    const res = num1+num2;
    callback(res);
    return res;
}


function mostrar_resultado(res){
    console.log(res)
}

calcular_soma(2,2,mostrar_resultado); //Função sendo usada como parametro de outra função, isso é o callback
