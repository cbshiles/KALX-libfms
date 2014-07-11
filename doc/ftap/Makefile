html:
	pandoc --include-in-header ftap.css -s --mathjax -i -t revealjs -o index.html ftap.md

rsync:
	rsync index.html kal@web69.webfaction.com:webapps/kalx/ftap

