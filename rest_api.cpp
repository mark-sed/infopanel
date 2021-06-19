#include <future>
#include <list>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/cURLpp.hpp>
#include "libs/json.hpp"
#include "rest_api.hpp"
#include "ip_exceptions.hpp"

using json = nlohmann::json;

// More: https://stackoverflow.com/a/41974669
std::future<std::string> RestAPI::POST(std::string const& url, std::string const& body) {
  return std::async(std::launch::async,
    [](std::string const& url, std::string const& body) mutable {
      std::list<std::string> header;
      header.push_back("Content-Type: application/json");
      
      curlpp::Cleanup clean;
      curlpp::Easy r;
      r.setOpt(new curlpp::options::Url(url));
      r.setOpt(new curlpp::options::HttpHeader(header));
      r.setOpt(new curlpp::options::PostFields(body));
      r.setOpt(new curlpp::options::PostFieldSize(body.length()));

      std::ostringstream response;
      r.setOpt(new curlpp::options::WriteStream(&response));

      r.perform();

      return std::string(response.str());
    }, url, body);
}

std::future<std::string> RestAPI::GET(std::string const& url) {
  return std::async(std::launch::async,
    [](std::string const& url) mutable {
      curlpp::Cleanup clean;
      curlpp::Easy r;
      r.setOpt(new curlpp::options::Url(url));
      std::ostringstream response;
      r.setOpt(new curlpp::options::WriteStream(&response));
      r.perform();
      return std::string(response.str());
    }, url);
}

static std::string format_price(float price){
    std::stringstream ss;
    int precision = 2;
    std::string postfix = "";
    // FIXME: Add even more postfixed in case a small currency is used
    if(price < 0.0f){
        precision = 4;
    }
    else if(price < 10.0f){
        precision = 3;
    }
    else if(price < 100.0f){
        precision = 2;
    }
    else if(price < 10'000.0f){
        precision = 1;
    }
    else if(price >= 10'000.0f){
        precision = 1;
        postfix = "k";
        price /= 1000;
    }

    ss << std::fixed << std::setprecision(precision) << price;
    return ss.str();
}

static std::string format_percentage(float percentage){
    std::stringstream ss;
    int precision = 1;
    if(std::abs(percentage) < 10.0f){
        precision = 2;
    }
    ss << std::fixed << std::setprecision(precision) << percentage;
    return ss.str();
}

void APIStocks::draw(LEDMatrix &matrix){
    const std::string SEPARATOR = "   ";
    const std::string GAIN_SYM = "+";
    const std::string LOSS_SYM = "";
    std::vector<std::string> symbols = this->conf.get_stocks_symbols();
    std::string key = this->conf.get_stocks_url_values_key();
    std::string color_text = this->conf.get_rest_color_symbol();
    std::string color_gain = this->conf.get_rest_color_gain();
    std::string color_loss = this->conf.get_rest_color_loss();
    std::string color_price = this->conf.get_rest_color_price();
    std::string color_neutral = this->conf.get_rest_color_neutral();
    
    std::string color_change = color_neutral;
    std::stringstream text;
    // Get values of each symbol (finnhub allowes only 1 symbol to be quoted at a time)
    for(std::string sym : symbols){
        // TODO: Add delay in case there are more than 30 request (limit is 30 calls per minute)
        auto r = GET("https://finnhub.io/api/v1/quote?symbol="+sym+"&token="+key);
        json data;
        std::string r_str = r.get();
        std::string percentage = "N/A";
        std::string curr_price = "N/A";
        std::string change_symbol = "";
        try{
            data = json::parse(r_str);

            // Check if current price and previous close price is present
            if(data.count("c") == 0 || data.count("pc") == 0){
                Warning::warning(std::string("Missing key in response JSON for symbol '"+sym+"' in APIStocks").c_str(), 
                                std::string("Response received: "+r_str).c_str());
            }

            float fprev_p = data["pc"].get<float>();
            float fcurr_p = data["c"].get<float>();
            float fperc = 0.0f;
            if(fprev_p != 0.0f){
                fperc = ((fcurr_p - fprev_p)/fprev_p)*100;
                if(fperc > 0.0f){
                    color_change = color_gain;
                    change_symbol = GAIN_SYM;
                }
                else{
                    color_change = color_loss;
                    change_symbol = LOSS_SYM;
		        }
            }
            curr_price = format_price(fcurr_p);
            percentage = format_percentage(fperc);
        }catch(json::exception &e){
            Warning::warning(std::string("An error occured when parsing response JSON for symbol '"+sym+"' in APIStocks").c_str(), 
                            std::string("Response received: "+r_str).c_str());
        }
        // TODO: Add possibility to display dolar/euro... symbol as well
        text << color_text << sym << " " << color_change << change_symbol << percentage << " %" << color_price << "(" << curr_price << ")" << color_text << SEPARATOR;
    }
    // FIXME: Pass in font based on config
    FontAscii font;
    matrix.draw_text(text.str(), font);
}

bool APIStocks::is_active() {
    // Get request if market is open
    auto r = GET("https://api.polygon.io/v1/marketstatus/now?&apiKey="+this->conf.get_stocks_url_market_open_key());
    json data;
    std::string r_str = r.get();
    try{
        data = json::parse(r_str);
    }catch(json::exception &e){
        Warning::warning("An error occured when parsing response JSON in APIStocks when checking for if the market is open", 
                         std::string("Response received: "+r_str).c_str());
        return false;
    }

    // Extract "market" value
    if(data.count("market") == 0){
        Warning::warning("Missing key in JSON response in APIStocks when checking for if the market is open", 
                         std::string("Response received: "+r_str).c_str());
        return false;
    }
    return data["market"].get<std::string>() == std::string("open");
}

void APICrypto::draw(LEDMatrix &matrix){

}
