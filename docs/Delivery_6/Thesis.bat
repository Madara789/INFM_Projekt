pdflatex -file-line-error -interaction=nonstopmode -synctex=1 -output-format=pdf DeliverableTemplate.tex
bibtex DeliverableTemplate
pdflatex -file-line-error -interaction=nonstopmode -synctex=1 -output-format=pdf DeliverableTemplate.tex
pdflatex -file-line-error -interaction=nonstopmode -synctex=1 -output-format=pdf DeliverableTemplate.tex
del *.aux *.bbl *.blg *.gz