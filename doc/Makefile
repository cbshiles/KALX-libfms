LESS = $(wildcard lesson*.md)
SOLN = $(wildcard solutions*.md)
HTML = index.html final.html $(LESS:.md=.html) $(SOLN:.md=.html) quiz.html

$(HTML): %.html: %.md
	pandoc -S --mathjax -H header.html -B before.html -A after.html $< -o $@

$(HTML): header.html before.html after.html main.css

ifm:
	pandoc --smart --css main.css -o ifm.html ifm.md
#	pandoc --smart -o ifm.pdf ifm.md

rsync: index.html $(HTML)
	rsync main.css $(HTML) kal@web69.webfaction.com:webapps/kalx/libfms

clean:
	rm -f $(HTML)
