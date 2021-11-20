# Info Panel

RaspberryPI based display panel (LED matrix) API to display stuff like stock prices and other "useful" stuff

# Making it run
`config.json.fill` has to be renamed to `config.json` and API keys should be filled in same as symbols to display.

Then `Makefile` can be used to compile the program and then the program needs to be ran with sudo privileges. Alternatively `&` can be appended at the end to make the program run in the background and free up your terminal.
```
make && sudo ./infopanel.out
```

## What needs to be setup
* Libcurl - `sudo apt-get install libcurl4-gnutls-dev`
* Python3 for REST API and its packages conatined inside of requirement.txt (`pip install -r requirements.txt`)
* Essential tools which should be already installed in most cases - `sudo apt-get install build-essential`
* SSH enabled for easier access to RaspberryPI from other computer

# Applications

Infopanel offers multiple built in application that can draw to the panel. Some of these need to be setup in `config.json` file (a copy of config.json.fill which needs to be made).

## Wall clock

It's just what it sounds like.

## Stock market values

Application for displaying current stock market values for selected companies (the ones written in config at `symbols` attribute as an array).

To make this work values need to be filled in the configuration file at `rest_api` -> `stocks`:
* `url_values_key` - your api key to [finnhub.io](https://finnhub.io/dashboard).
* `url_market_open_key` - your api key to [polygon.io](https://polygon.io/dashboard/api-keys).

It uses 2 APIs to get market values (finnhun.io) and to check if the market is open or closed (polygon.io). Both of these APIs can be used for free.

## Cryptocurrecy values

Similar to stocks application, but for cryptocurrency values. And just as like in the stocks application the `symbol` attribute in configuration file needs to be filled in with the wanted cryptocurrencies to be displayed.

