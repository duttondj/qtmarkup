# qtmarkup
QtMarkup is a Qt application that will generate HTML from a simplified markup language. C-o will open a file dialog box where you can select your simple markup file or you can type in whatever simple markup you want in the left box. C-s will save the generated HTML in the right box.

## Compiling
Run `cmake CMakeLists.txt` to generate a Makefile then run `make` to compile the binary.

## Testing
Running `make test` after running `make` will run the test code on qtmarkup and will generate a logfile called testqtmarkup.log.txt
