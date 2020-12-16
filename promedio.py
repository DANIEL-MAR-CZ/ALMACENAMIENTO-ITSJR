#IMPORTAMOS LIBRERIASS
#import libraries
import sys
import requests
from dateutil import parser
from pyspark.sql import SparkSession
from pyspark.sql import functions as F
from pyspark.sql.types import BooleanType

#filter, date
fecha1 = ''
fecha2 = ''

if __name__ == "__main__":
    """
        Usage: promedio [fecha1][fecha2]
    """
#sesion
#spark = SparkSession.builder.appName('example').getOrCreate()
    spark = SparkSession \
        .builder \
        .appName("PROMEDIOS RANGO") \
        .getOrCreate()

    if len(sys.argv) > 2:
        fecha1 = parser.parse(sys.argv[1]).strftime('%Y-%m-%d')
        fecha2 = parser.parse(sys.argv[2]).strftime('%Y-%m-%d')
    else:
        sys.exit("Faltan argumentos, deben de ser 2 Fechas")


    def getDataFromApi():
        url = "http://144.202.34.148:3003/api/getbotones"
        response = requests.get(url)
        return response

#Range
    @F.udf(returnType=BooleanType())
    def my_fil(fec):
        fechav = parser.parse(fec).strftime('%Y-%m-%d')
        return fecha1 <= fechav <= fecha2

    print("-------------------------------- INICIA PROGRAMA CHIDO ---------------------")
    data = getDataFromApi()
    json_rdd = spark.sparkContext.parallelize([data.text])
    df = spark.read.json(json_rdd)
    filtro = df.select("distancia").filter(my_fil(df["fecha"]))
    result = filtro.agg(F.min(df["distancia"]), F.avg(df["distancia"]))
    print("EL PROMEDIO DE LOS ESTADOS EN on DETECTADOS ES:  ")
    print(result.show(truncate=False))


    print("end")
    #end process core
    spark.stop()
