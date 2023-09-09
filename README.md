# Feather

A C++ **game engine** project composed of multiple open source modules. Previously, this project was being built as a monolitic static library and had a simple logging system, a math library, an entity component system, a single window manager and OpenGL facilities. However, the state of the code wasn't satisfactory, so a [hard reset](https://github.com/pedrolmcastro/feather/commit/a049ccbba7c2f9d6d2a1e792eeb103802d0b141b) was made and the project pivoted to developing smaller **independent modules** and gluing them together.


## Modules

- [x] [sos: safety runtime checks facility](https://github.com/pedrolmcastro/sos)
- [ ] (planned): math library
- [ ] (planned): logging library
- [ ] (planned): platform detection
- [ ] (planned): entity component system
- [ ] (todo): physics engine
- [ ] (todo): reflection facility
- [ ] (todo): serialization library
- [ ] (todo): audio system
- [ ] (todo): assets manager
- [ ] (todo): window manager
- [ ] (todo): renderer abstraction layer


## About this project

This is an experimental project developed to learn about low-level API design and modern C++ practices. It is possible that the engine will never be completed.


## Other engines and resources

- [The Chernos's Hazel](https://github.com/TheCherno/Hazel)
- [The Chernos's Sparky](https://github.com/TheCherno/Sparky)
- [Travis Vroman's Kohi](https://github.com/travisvroman/kohi)
- [Tartarus Game Engine](https://youtube.com/playlist?list=PLj35Ys9AmS0POIYCV3VigykLzPJvdvig7&si=_yhZ2bUhTvA4gqf2)
- [Ozzadar Dev's Youtube Engine](https://github.com/mauville-technologies/youtube-engine)
- [Arash Khatami's Game Engine Series](https://youtube.com/playlist?list=PLU2nPsAdxKWQYxkmQ3TdbLsyc1l2j25XM&si=Rin9S8tz9tJWLlrF)
- [GamesWithGabe's Java Game Engine](https://youtube.com/playlist?list=PLtrSb4XxIVbp8AKuEAlwNXDxr99e3woGE&si=QNUg34eZ_UHA8Fwa)
