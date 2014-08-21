CHAPTERS = background.md finance.md
# mathematics.md software.md
TOC = --toc --toc-depth=2

all: book

book: epub html pdf

clean:
	rm -r fms.epub fms.html fms.pdf

epub: fms.epub

html: fms.html

pdf: fms.pdf

fms.epub: $(CHAPTERS)
	pandoc $(TOC) -S -o $@ $^

fms.html: $(CHAPTERS)
	pandoc $(TOC) -f markdown+definition_lists+example_lists \
	--css fms.css -H header.html -s --mathjax \
	-S -o $@ $^

fms.pdf: $(CHAPTERS)
	pandoc $(TOC) -f markdown+definition_lists+example_lists \
	-N -o $@ $^

rsync:
	rsync index.html kal@web69.webfaction.com:webapps/kalx/ftap

