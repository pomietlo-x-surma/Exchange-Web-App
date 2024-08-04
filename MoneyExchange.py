import requests as r
from bs4 import BeautifulSoup
import sys

curr = {
    'zloty': ('PLN', 'zł'),
    'dollar': ('USD', '$'),
    'euro': ('EUR', '€'),
    'pound': ('GBP', '£'),
    'hryvna': ('UAH', '₴'),
    'dinar': ('TND', 'DT')
}


def get_currency(currency1, currency2):
    try:
        if currency1 == currency2:
            return curr[currency2][1]
        if type(currency1) is not str or type(currency2) is not str:
            raise TypeError("Zły typ danych!")
        else:
            url = f'https://www.google.com/finance/quote/{curr[currency1][0]}-{curr[currency2][0]}'
            page = r.get(url)
            soup = BeautifulSoup(page.text, 'html.parser')
            res = soup.find_all('div', attrs={'class': 'YMlKec fxKbKc'})
            res = float([x.text for x in res][0].replace(',', ''))
            # Extract chart SVG from 1D
            #need to add more date options
            chart_div = soup.find('div', attrs={'class': 'ushogf'})
            if chart_div:
                svg = chart_div.find('svg')
                if svg:
                    svg_content = str(svg)
                    return res, curr[currency2][1], svg_content
            return res, curr[currency2][1], None
    except ValueError:
        raise ValueError("Wystąpił błąd!")
    except Exception as e:
        print(f"Błąd: {e}")





if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Użycie: MoneyExchange.exe [currency1] [currency2]")
    else:
        currency1 = sys.argv[1].lower()
        currency2 = sys.argv[2].lower()
        result = get_currency(currency1, currency2)
        print(f"Exchange Rate: {result[0]} {result[1]}")
        if result[2]:
            print("Chart SVG:")
            print(result[2])
        else:
            print("No chart found.")
