# Compass Redux

Compass (redux) aims to provide a lightweight, *simple* and *small* platform to create and run interactive fiction pieces. So far, it's nothing. This document is, pretty much, a roadmap to be taken with a handful of salt.

## The Language

The language's design and "aesthetic" is very much a work-in-progress, and will probably change a lot in early development. The main goals as of the writing of this documents are:

 - be *simple*. I love Inform7's approach, especially from a computer nerdery standpoint. But I sometimes find that it gets so close to english that it's a struggle to know what will and won't work, because it's not *quite* english. I want Compass to avoid that if possible.
 - avoid heavy markup: again, I think Inform7's approach of *stating how things are* is quite lovely.
 - be extensible: directions shouldn't be limited to north/south/east/west, you should be able to create new ones inside a story, for example. Same with properties

## The VM

The VM should be small (my ultimate goal is for it to be able to run on something like an Arduino). It shouldn't try to be generalist, but rather tailored for interactive fiction.
