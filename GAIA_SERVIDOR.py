import serial
import app
from flask import Flask, jsonify
from flask import render_template
import time
import datetime 

app = Flask(__name__,template_folder='C:/Users/gdepa/OneDrive/Área de Trabalho/TRABALHOS IF/Robótica/GAIA/templates')

timestamp = datetime.datetime.now().strftime("%Y-%m-%dT%H-%M-%S-%f")
beginMarker="<"
endMarker=">"
now= datetime.datetime.now()
nomeArquivo = f"{timestamp}.txt"
arquivo = open(nomeArquivo, "a")  
arduino = serial.Serial(port='COM4', baudrate= 9600,)

def readArduino():
    global endMarker
    global beginMarker
    KeyChars= "<>"
    mensagem=""
    luz=""
    temperatura=""
    umi_ar=""
    umi_s=""

    while arduino.inWaiting() >0:
        mensagem += arduino.readline(1).decode()
    
    if(beginMarker in mensagem and endMarker in mensagem):
        for character in KeyChars:
            mensagem=mensagem.replace(character, "")
        x=mensagem.split(", ")
        luz= x[0]
        temperatura=x[1]
        umi_ar=x[2]
        umi_s= x[3]
        print(mensagem)
        print(luz)
        print(temperatura)
        print(umi_ar)
        print(umi_s)

        
        arquivo.write(mensagem+"\r\n")
        arduino.reset_input_buffer()
        return mensagem, luz, temperatura, umi_ar, umi_s
    else:
        return "", 0, 0, 0, 0



@app.route('/')
@app.route('/gaia')
def index():
    mensagem, luz, temperatura, umi_ar, umi_s=readArduino()
    return render_template("dados_gaia.html", mensagem=mensagem, luz=luz, temperaura=temperatura, umi_ar= umi_ar, umi_s=umi_s)
@app.route('/dados')
def obter_dados():
    mensagem, luz, temperatura, umi_ar, umi_s = readArduino()
    if mensagem:
        try:
            luz1 = float(luz)
            temperatura1 = float(temperatura)
            umi_ar1 = float(umi_ar)
            umi_s1 = float(umi_s)

            dados = [mensagem, luz1, temperatura1, umi_ar1, umi_s1]
            print(f"DADOS JSON: {dados}")
            return jsonify(dados)
        except ValueError as e:
            print("Erro ao converter valores:", e)
            return jsonify([])
    else:
        return jsonify([])


if __name__ == '__main__':
    with app.app_context():
        app.run()
        obter_dados()
      
       


arduino = serial.Serial(port='COM4', baudrate= 9600,)



    


