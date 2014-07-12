MD = $(wildcard lesson*.md)
HTML = index.html $(MD:.md=.html)

all: $(HTML)

$(HTML): %.html: %.md
	pandoc -S --mathjax -H header.html -B before.html -A after.html $< -o $@

$(HTML): header.html before.html after.html main.css

rsync: index.html $(HTML)
	rsync main.css $(HTML) kal@web69.webfaction.com:webapps/kalx/libfms

clean:
	rm -f $(HTML)
