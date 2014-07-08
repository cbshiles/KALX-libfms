HTML = index.html lecture1.html

all: $(HTML)

$(HTML): %.html: %.md
	pandoc -H header.html -B before.html -A after.html $< -o $@

clean:
	rm $(HTML)
