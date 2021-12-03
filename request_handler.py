import json
import stockpanel
import threading


def hello():
    return stockpanel.hello()

def setBrightness(value):
    return stockpanel.setBrightness(value)

def showStocks():
    return stockpanel.showStocks()

def toggleLamp():
    return stockpanel.toggleLamp()

def toggleDisplay():
    return stockpanel.toggleDisplay()

def showClock():
    return stockpanel.showClock()
    
def setCurrency(name):
    return stockpanel.setCurrency(name)

def setFinhubKey(key):
    return stockpanel.setFinhubKey(key)

def setPolygonKey(key):
    return stockpanel.setPolygonKey(key)

def setScheduler(jsonStr):
    return stockpanel.setScheduler(jsonStr)

def setColorSymbol(code):
    return stockpanel.setColorSymbol(code)

def setColorPrice(code):
    return stockpanel.setColorPrice(code)

def setColorGain(code):
    return stockpanel.setColorGain(code)

def setColorLoss(code):
    return stockpanel.setColorLoss(code)

def setColorNeutral(code):
    return stockpanel.setColorNeutral(code)

def getSettings():
    return stockpanel.getSettings()

def getBrightness():
    return stockpanel.getBrightness()

def getScheduler():
    return stockpanel.getScheduler()

def getDisplayStatus():
    return stockpanel.getDisplayStatus()

def getLampStatus():
    return stockpanel.getLampStatus()

def initPanel():
    return stockpanel.initPanel()

def runPanel():
    return stockpanel.runPanel()
