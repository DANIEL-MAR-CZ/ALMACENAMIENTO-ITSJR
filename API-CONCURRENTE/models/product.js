'use strict'
//creamos el esquema/modelo de los campos de nuestra bd de mongo
const mongoose = require('mongoose')
const Schema = mongoose.Schema 

const ProductSchema = Schema({
    boton:String,
    posicion:String
    

})

module.exports = mongoose.model('product', ProductSchema) 
