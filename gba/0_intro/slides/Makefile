OBJS=class.pdf
LATEX=xelatex

all: $(OBJS)

%.pdf: %.tex  %.bib
	$(LATEX) -shell-escape $(basename $@)
	bibtex  $(basename $@)
	$(LATEX) -shell-escape $(basename $@)
	$(LATEX) -shell-escape $(basename $@)

.PHONY: clean

clean:
	rm -f *.{aux,bbl,blg,pdf,log,nav,out,snm,toc,vrb}
	rm -rf _minted-class_1
