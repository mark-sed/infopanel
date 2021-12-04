"""
Main handler for API requests
:Author: Marek Sedlacek
"""

import json
import stockpanel
from server.swagger_server.models.scheduler import Scheduler 
from sys import argv

def is_dummy():
    """
    :return True if dummy mode is set 
    """
    return len(argv) > 1 and (argv[1] == "-d" or argv[1] == "--dummy")

def rgb2grb(rgb):
    """
    Converts rgb hex string into grb hexstring
    """
    return "0x"+rgb[4:6]+rgb[2:4]+rgb[6:8]

def grb2rgb(grb):
    """
    Converts grb hex string into rgb hexstring
    """
    return "0x"+grb[4:6]+grb[2:4]+grb[6:8]

def hello():
    """
    Ping response
    """
    if is_dummy():
        return "Pong"
    return stockpanel.hello()

def setBrightness(value):
    """
    Sets brightness of the panel
    """
    if is_dummy():
        return True
    return stockpanel.setBrightness(value)

def showStocks():
    """
    Interrupts scheduler to display stocks
    """
    if is_dummy():
        return True
    return stockpanel.showStocks()

def toggleLamp():
    """
    Toggles panel into lamp mode
    """
    if is_dummy():
        return True
    return stockpanel.toggleLamp()

def toggleDisplay():
    """
    Toggles display on or off
    """
    if is_dummy():
        return True
    return stockpanel.toggleDisplay()

def showClock(time_sec):
    """
    Interrupts scheduler to display clock
    :param time_sec Seconds for how long the time should be displayed
    """
    if is_dummy():
        return True
    return stockpanel.showClock(time_sec if time_sec is not None else 10)
    
def setCurrency(name):
    """
    Sets used currency
    :param name Currency name
    """
    if is_dummy():
        return True
    return stockpanel.setCurrency(name)

def setFinhubKey(key):
    """
    Sets Finhub API key
    :param key API key
    """
    if is_dummy():
        return True
    return stockpanel.setFinhubKey(key)

def setPolygonKey(key):
    """
    Sets Polygon key
    :param key API key
    """
    if is_dummy():
        return True
    return stockpanel.setPolygonKey(key)

def setScheduler(jsonStr):
    """
    Sets scheduler
    :param jsonStr JSON string with the scheduler
    """
    if is_dummy():
        return True
    return stockpanel.setScheduler(jsonStr)

def setColorSymbol(code):
    """
    Sets color for symbol
    :param color New Color
    """
    if is_dummy():
        return True
    return stockpanel.setColorSymbol(rgb2grb(code))

def setColorPrice(code):
    """
    Sets color for price
    :param color New Color
    """
    if is_dummy():
        return True
    return stockpanel.setColorPrice(rgb2grb(code))

def setColorGain(code):
    """
    Sets color for gain
    :param color New Color
    """
    if is_dummy():
        return True
    return stockpanel.setColorGain(rgb2grb(code))

def setColorLoss(code):
    """
    Sets color for loss
    :param color New Color
    """
    if is_dummy():
        return True
    return stockpanel.setColorLoss(rgb2grb(code))

def setColorNeutral(code):
    """
    Sets color for neutral
    :param color New Color
    """
    if is_dummy():
        return True
    return stockpanel.setColorNeutral(rgb2grb(code))

def getSettings():
    """
    :return Current settings
    """
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
    settings_json = json.loads(stockpanel.getSettings())
    settings_json["colors"]["symbol"] = grb2rgb(settings_json["colors"]["symbol"])
    settings_json["colors"]["price"] = grb2rgb(settings_json["colors"]["price"])
    settings_json["colors"]["gain"] = grb2rgb(settings_json["colors"]["gain"])
    settings_json["colors"]["loss"] = grb2rgb(settings_json["colors"]["loss"])
    settings_json["colors"]["neutral"] = grb2rgb(settings_json["colors"]["neutral"])
    return json.dumps(settings_json)

def getBrightness():
    """
    :return Current brightness
    """
    if is_dummy():
        return json.dumps({"value": 42})
    return stockpanel.getBrightness()

def getScheduler():
    """
    :return Current scheduler settings
    """
    if is_dummy():
        return json.dumps(
        {
        "widgets": {
            "stocks": [
            {
                "position": 0,
                "duration": {
                    "multiplicator": True,
                    "value": 1
                },
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
                "duration": {
                    "multiplicator": True,
                    "value": 1
                },
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
                "duration": {
                    "multiplicator": False,
                    "value": 10
                },
                "format24hr": True,
                "font": "Ascii",
                "type": "Pixelated"
            }
            ]
        }
        })
    return stockpanel.getScheduler()

def getDisplayStatus():
    """
    :return Current display status (ON/OFF)
    """
    if is_dummy():
        return json.dumps({"isOn": True})
    return stockpanel.getDisplayStatus()

def getLampStatus():
    """
    :return If the lamp is ON/OFF
    """
    if is_dummy():
        return json.dumps({"isOn": True})
    return stockpanel.getLampStatus()

def initPanel():
    """
    Initializes panel
    """
    return stockpanel.initPanel()

def runPanel():
    """
    Runs one panel iteration
    """
    return stockpanel.runPanel()
