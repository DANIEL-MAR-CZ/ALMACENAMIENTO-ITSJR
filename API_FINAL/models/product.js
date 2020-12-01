'use strict'
//creamos el esquema/modelo de los campos de nuestra bd de mongo
const mongoose = require('mongoose')
const Schema = mongoose.Schema 

const ProductSchema = Schema({
    boton:Number,
    posicion:String,
    distancia:Number,
    fecha:Date
    

})

module.exports = mongoose.model('product', ProductSchema) 
