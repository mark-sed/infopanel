import json
import stockpanel
from server.swagger_server.models.scheduler import Scheduler 
from sys import argv

def is_dummy():
    return len(argv) > 1 and (argv[1] == "-d" or argv[1] == "--dummy")

def hello():
    if is_dummy():
        return "Pong"
    return stockpanel.hello()

def setBrightness(value):
    if is_dummy():
        return True
    return stockpanel.setBrightness(value)

def showStocks():
    if is_dummy():
        return True
    return stockpanel.showStocks()

def toggleLamp():
    if is_dummy():
        return True
    return stockpanel.toggleLamp()

def toggleDisplay():
    if is_dummy():
        return True
    return stockpanel.toggleDisplay()

def showClock(time_sec):
    if is_dummy():
        return True
    return stockpanel.showClock(time_sec if time_sec is not None else 10)
    
def setCurrency(name):
    if is_dummy():
        return True
    return stockpanel.setCurrency(name)

def setFinhubKey(key):
    if is_dummy():
        return True
    return stockpanel.setFinhubKey(key)

def setPolygonKey(key):
    if is_dummy():
        return True
    return stockpanel.setPolygonKey(key)

def setScheduler(jsonStr):
    if is_dummy():
        return True
    return stockpanel.setScheduler(jsonStr)

def setColorSymbol(code):
    if is_dummy():
        return True
    return stockpanel.setColorSymbol(code)

def setColorPrice(code):
    if is_dummy():
        return True
    return stockpanel.setColorPrice(code)

def setColorGain(code):
    if is_dummy():
        return True
    return stockpanel.setColorGain(code)

def setColorLoss(code):
    if is_dummy():
        return True
    return stockpanel.setColorLoss(code)

def setColorNeutral(code):
    if is_dummy():
        return True
    return stockpanel.setColorNeutral(code)

def getSettings():
    if is_dummy():
        return json.dumps(
            {
            "brightness": 42,
            "currency": "usd",
            "finhubKey": "1242DEADBEEF456",
            "polygonKey": "314159265ABC",
            "colors": {
                "symbol": "0xFCBA03",
                "price": "0xFCBA03",
                "gain": "0x10AA10",
                "loss": "0xAA1010",
                "neutral": "0xFCBA03"
                }
            }
        )
    return stockpanel.getSettings()

def getBrightness():
    if is_dummy():
        return json.dumps({"value": 42})
    return stockpanel.getBrightness()

def getScheduler():
    if is_dummy():
        return json.dumps(
        {
        "widgets": {
            "stocks": [
            {
                "position": 0,
                "tickers": [
                    "NIO", "F", "INTC"
                ],
                "showPrice": True,
                "showPercentage": True
            }
            ],
            "crypto": [
            {
                "position": 1,
                "tickers": [
                    "bitcoin", "ethereum"
                ],
                "showPrice": True,
                "showPercentage": True
            }
            ],
            "clock": [
            {
                "position": 2,
                "format24hr": True,
                "font": "Ascii",
                "type": "Pixelated"
            }
            ]
        }
        })
    return stockpanel.getScheduler()

def getDisplayStatus():
    if is_dummy():
        return json.dumps({"isOn": True})
    return stockpanel.getDisplayStatus()

def getLampStatus():
    if is_dummy():
        return json.dumps({"isOn": True})
    return stockpanel.getLampStatus()

def initPanel():
    return stockpanel.initPanel()

def runPanel():
    return stockpanel.runPanel()
