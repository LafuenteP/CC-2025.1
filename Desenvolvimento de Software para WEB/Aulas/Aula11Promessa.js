const callback = () => {}

function getPromiseAPI(){
    //Comunicação externa com a base de dados remota...
    let myPromise = new Promise(
        (resolve, reject) => {
            const num = 4;
            if(num%2 == 0) resolve("ok, número par");
            else reject("NOK, número ímpar");
        }
    )
    return myPromise;
}

function clientAPI(){
    console.log(getPromiseAPI("http://fake.com/dados"))
    .then(
        (res) => console.log("Tudo certo!")
    )
    .catch(
        (res) => console.log("Error")
    )
    .finally(
        (res) => console.log("Termino da operacao")
    )
}

clientAPI();

// .then() - executa caso ele consiga pegar os dados
// .catch() - executa caso ele não consiga pegar os dados
// .finally() - executa independente do que aconteça


//setTimeout(() => {}, 3000) isso tá chamando uma função que executa depois de 3000 milisegundos, que é 3 segundos

//async | await - Usar await antes de uma função quer dizer que ela espera o que estiver sendo feito antes para ser executada
// porém o js obriga essa função ser async, pois senão todas que precisam do client depois dela iriam ter que esperar também.
