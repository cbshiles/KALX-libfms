MD = $(wildcard lesson*.md)
HTML = $(MD:.md=.html)

all: index.html $(HTML)

$(HTML): %.html: %.md
	pandoc -S -H header.html -B before.html -A after.html $< -o $@

index.html: index.md
	pandoc -S -H header.html -A after.html $< -o $@

$(HTML): header.html before.html after.html

rsync: index.html $(HTML)
	rsync index.html $(HTML) kal@web69.webfaction.com:webapps/kalx/libfms

clean:
	rm -f $(HTML)
