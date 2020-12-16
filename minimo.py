#IMPORTAMOS LIBRERIASS
#import libraries
import requests

from pyspark.sql import SparkSession
from pyspark.sql import functions as F



if __name__ == "__main__":
    """
        Usage: minimo
    """
#sesion
#spark = SparkSession.builder.appName('example').getOrCreate()
    spark = SparkSession \
        .builder \
        .appName("PR2_MINIMO") \
        .getOrCreate()



#connect to api
    def getDataFromApi():
        url = "http://144.202.34.148:3003/api/getbotones"
        response = requests.get(url)
        return response


    print("-------------------------------- INICIA PROGRAMA CHIDO ---------------------")
    data = getDataFromApi()
    json_rdd = spark.sparkContext.parallelize([data.text])
    df = spark.read.json(json_rdd)
    result = df.select("distancia").agg(F.min(df["distancia"]))
    print(result.show(truncate=False))
    print("EL MINIMO DE LOS ESTADOS EN on FUERON:  ")
    print(result.show(truncate=False))


    print("end")
    #end process core
    spark.stop()
