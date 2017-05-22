# Bruno Mondelo Giaramita                                    
# mondelob14@gmail.com                                       
# isx48185462                                                
# Escola del Treball de Barcelona 2017-05-20

.SILENT:

# Convert to dzslides
PANDOC=pandoc --standalone --to dzslides
INCREMENTAL=#--incremental
STYLE=#--css=

# The conversion files
TARGETS=msue.html

# The style files
STYLES=style.css

# RULES
all: $(TARGETS)

msue.html: msue.md
	echo "Creating slides for $@"
	$(PANDOC) $(INCREMENTAL) $(STYLE)$(STYLES) $< -o $@

# The utilities
build: clean all

show:
	echo "Showing slides..."
	firefox msue.html

clean:
	echo "Cleaning all targets"
	rm -f $(TARGETS)
