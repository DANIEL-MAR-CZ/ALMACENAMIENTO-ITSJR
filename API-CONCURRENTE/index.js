//CREATED: 19-10-20 BY: EQUIPO-NARANJA
'use strict'
//capas de conexion
const express = require('express')
const bodyParser = require('body-parser')
const mongoose = require('mongoose')

//DECLARAMOS LA RUTA DE NUESTRO ARCHIVO DE ESQUEMAS
const Product = require('./models/product.js')

const app= express()
const port = process.env.PORT || 3009

app.use(bodyParser.urlencoded({ extended: false }))
app.use(bodyParser.json())

/* //envio de parametros en el navegador http://localhost:3000/hola/daniel
app.get('/hola/:name',(req,res) => {
    res.send({ message: `HOlA ${req.params.name}!`}) 
}) */


// muestra todos los registros de la BD
app.get('/api/botones',(req, res) => {

    Product.find({}, (err, products) => {
        if(err) return res.status(500).send({message: `ERROR al realizar la peticion:${err}`})
        if(!products) return res.status(404).send({message:`NO EXISTEN REGISTROS`})

        res.send(200, { products })
    })
})


// muestra un registro especifico mdediante ID
app.get('/api/product/:botonesId',(req, res) => {

    let botonesId = req.params.botonesId

    Product.findById(botonesId, (err,product) => {
        if(err) return res.status(500).send({message: `ERROR al realizar la peticion:${err}`})
        if(!product) return res.status(404).send({message:`El registro NO existe`})

        res.status(200).send({ product })
    })
   
})


app.post('/api/botones',(req, res) => {
    /*
    console.log(req.body)
    res.status(200).send({message: 'el producto se ha recibido'}) */
    console.log('POST /api/botones')
    console.log(req.body)

    let product = new Product()
 
    product.boton = req.body.boton
    product.posicion = req.body.posicion

    product.save((err, productStored) =>{
      if (err) res.status(500).send({message: `¡¡ERRRROR! al guardar la base de datos: ${err}` })
           res.status(200).send({product: productStored})
       })
})
 
app.put('/api/botones/:productId',(req, res) => {
   
})
app.delete('/api/botones/:botonesId',(req, res) => {
    let botonesId = req.params.botonesId

    Product.findById(botonesId, (err,product) => {
        if(err) res.status(500).send({message: `ERROR al borrar el registro:${err}`})
    

       product.remove(err => {
        if (err) res.status(500).send({message: `¡¡ERRRROR! al borrar el registro: ${err}` })
        res.status(200).send({message: 'El registro ha sido eliminado EXITOSAMENTE'})
       }) 
   })
})

//mongoose.connect('mongodb://localhost:27017/apagador', (err,res) =>{
    
mongoose.connect('mongodb://localhost:27017/apagador', { 'useNewUrlParser': true, 'useUnifiedTopology': true }, (err) =>{
   if(err){
     return console.log(`ERRROR al conectar a la base de datos: ${err}`)
    }
   console.log('conexion a la base de datos exitosa...')
   
   app.listen(port,() => {
     console.log(`API REST corriendo en http://localhost:${port}`)
    })

})


