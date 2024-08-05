import requests as r
from bs4 import BeautifulSoup
import matplotlib.pyplot as plt
from PIL import Image
from io import BytesIO

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
            return 1.0, curr[currency2][1], None
        if currency1 not in curr or currency2 not in curr:
            raise ValueError(f"Unsupported currency: {currency1} or {currency2}")

        url = f'https://www.google.com/finance/quote/{curr[currency1][0]}-{curr[currency2][0]}'
        url_chart = f'https://mybank.pl/kursy-walut/{curr[currency1][0].lower()}-{currency1.lower()}/'

        print(f"Fetching URL: {url}")

        page = r.get(url)
        if page.status_code != 200:
            raise Exception(f"Failed to fetch page, status code: {page.status_code}")

        soup = BeautifulSoup(page.text, 'html.parser')
        res = soup.find_all('div', attrs={'class': 'YMlKec fxKbKc'})
        if not res:
            raise ValueError("No exchange rate found on the page")

        res = float(res[0].text.replace(',', ''))

        # Fetching the chart
        print(f"Fetching URL: {url_chart}")
        page_2 = r.get(url_chart)
        if page_2.status_code != 200:
            raise Exception(f"Failed to fetch page, status code: {page_2.status_code}")

        soup_2 = BeautifulSoup(page_2.text, 'html.parser')
        img_tag = soup_2.find('img', id='wykres_sredni')
        if not img_tag:
            raise ValueError("No chart image found on the page")

        chart_url = img_tag['src']
        chart_img_response = r.get(chart_url)
        if chart_img_response.status_code != 200:
            raise Exception(f"Failed to download chart image, status code: {chart_img_response.status_code}")

        return res, curr[currency2][1], chart_img_response.content

    except ValueError as ve:
        print(f"Error: {ve}")
        return None

    except Exception as e:
        print(f"Error: {e}")
        return None

if __name__ == "__main__":
    currency1 = 'dollar'
    currency2 = 'zloty'
    result = get_currency(currency1, currency2)
    if result:
        print(f"Exchange Rate: {result[0]} {result[1]}")
        if result[2]:
            try:
                # Display the chart image
                img = Image.open(BytesIO(result[2]))
                plt.imshow(img)
                plt.axis('off')
                plt.show()
            except Exception as e:
                print(f"An error occurred: {e}")
        else:
            print("No chart found.")
    else:
        print("No data available.")




# if __name__ == "__main__":
#     if len(sys.argv) != 3:
#         print("Użycie: MoneyExchange.exe [currency1] [currency2]")
#     else:
#         currency1 = sys.argv[1].lower()
#         currency2 = sys.argv[2].lower()
#         result = get_currency(currency1, currency2)
#         print(f"Exchange Rate: {result[0]} {result[1]}")
#         if result[2]:
#             print("Chart SVG:")
#             print(result[2])
#         else:
#             print("No chart found.")
