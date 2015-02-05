MATHJAX="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"
#MATHJAX="MathJax-2.4-latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"

html:
	pandoc -s -i -H header.html --mathjax=${MATHJAX} -t revealjs -V theme:sky -V transition:slide -V center:false -o index.html ftap.md

latex:
	pandoc -r markdown+yaml_metadata_block -s -S --latex-engine=pdflatex \
	fms.md finance.md -o fms.tex

fms:
	pandoc -f markdown+definition_lists+example_lists \
	--css ftap.css -H header.html -s -S \
	--mathjax -o fms.html \
	background.md finance.md

rsync:
	rsync index.html kal@web69.webfaction.com:webapps/kalx/ftap

