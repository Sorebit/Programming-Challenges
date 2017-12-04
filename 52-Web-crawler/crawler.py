import urllib.request
from urllib.parse import urlparse
from bs4 import BeautifulSoup
import sys


print("Web crawler - Sorebit")
print("Written as part of Programming Challenges")
print("Basic, single-site crawling version")
url = input("Input (full) url to crawl: ")
print("Now crawling through " + url)

urls = [url] # stack of urls to scrape
visited = [url] # historic record of urls

while len(urls) > 0:
	try:
		htmltext = urllib.request.urlopen(urls[0])
	except:
		print(urls[0])
	soup = BeautifulSoup(htmltext, "html.parser")

	urls.pop(0)
	print(len(urls))

	for tag in soup.findAll('a', href = True):
		# print(tag['href'])
		tag['href'] = urllib.parse.urljoin(url, tag['href'])

		# If link is still on the original site and has not been visited
		if url in tag['href'] and tag['href'] not in visited:
			urls.append(tag['href'])
			visited.append(tag['href'])

print(visited)