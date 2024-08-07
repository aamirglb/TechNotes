from playwright.sync_api import sync_playwright

target_url = 'https://www.example.com'
element = 'h1'

with sync_playwright() as pw:
    webkit = pw.webkit
    browser = webkit.launch()
    browser_context = browser.new_context()
    page = browser_context.new_page()
    page.goto(target_url)
    found_element = page.locator(element)
    text = found_element.text_content()
    browser.close()

    print(text)