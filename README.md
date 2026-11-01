<h1 align="center">⛴️ Ferry</h1>

<p align="center">
  <strong>Carry your text across languages, without losing anything on the way.</strong>
</p>

<p align="center">
  A translation workspace for structured and plain text files, built to handle the hard parts:
  direction, scripts, shaping, bidi, numbers, and locales.
</p>

<p align="center">
  <!-- Replace with real badges -->
  <img alt="license" src="https://img.shields.io/badge/license-MIT-blue">
  <img alt="status" src="https://img.shields.io/badge/status-early%20development-orange">
  <img alt="PRs welcome" src="https://img.shields.io/badge/PRs-welcome-brightgreen">
</p>

---

## Why Ferry?

Translating a file is rarely just translating text. Real projects arrive as XML with
tags that must not break, CSVs with dozens of columns, JSON with placeholders, and
subtitles with strict timing. Once you add right-to-left languages, mixed-direction
sentences, different digit systems and locale rules, ordinary text editors stop being
helpful.

**Ferry is the boat that makes the crossing safe.** You bring a source file, choose
your target languages, and Ferry keeps structure intact, protects what must not be
touched, and gives translators tools that understand how real scripts behave.

## Core idea

```
            ┌──────────── Project ────────────┐
            │                                 │
 Source  ──►│   English (source)              │
 language   │      ├── Persian   ▓▓▓▓▓▓░░ 78% │
            │      ├── Arabic    ▓▓▓▓░░░░ 52% │
            │      ├── German    ▓▓▓▓▓▓▓▓ 100%│
            │      └── Japanese  ▓░░░░░░░ 12% │
            └─────────────────────────────────┘
```

1. **Create a project** from a source-language file.
2. **Add target languages** whenever you need them.
3. **Translate and watch progress** per language, per file, per item.
4. **Export** back to the original format, ready to ship.

## Features

### 🗂️ Projects and items
- Create projects from a source language and add or remove target languages at any time
- Per-language progress tracking (translated, in review, untranslated, changed in source)
- Import and export for single files or whole sets of files
- Organize items with groups, tags, filters, and search
- Detect when the source text changes and flag affected translations as outdated

### 📄 Many formats, one workflow
| Format | Typical use |
|--------|-------------|
| `.txt` | Plain text, line or paragraph based |
| `.xml` | App resources, documents, custom schemas |
| `.csv` | Spreadsheets and string tables |
| `.json` | App localization files, nested keys |
| `.srt` | Subtitles with timing preserved |
| *and more* | New formats are added through a simple parser/writer interface |

Round-tripping is a priority: what you import is what you export, with only the
translatable content changed.

### 🌍 Built for real-world scripts
Ferry treats language problems as first-class features, not afterthoughts:

- **Direction**: per-language and per-item LTR/RTL handling, with a clear visual preview
- **Bidi**: help with mixed-direction text (Latin words, numbers, or punctuation inside RTL sentences), including direction marks and isolates
- **Scripts and shaping**: correct rendering and checks for connected scripts such as Arabic and Persian, and for complex scripts in general
- **Numbers**: convert and validate digit systems (Western, Arabic-Indic, Persian) and number formatting
- **Locales**: locale-aware handling of plurals, dates, separators, and quotation marks
- **Unicode hygiene**: detect and clean invisible characters, mixed lookalike characters, and inconsistent normalization

### 🛡️ Safe by design
- Protect tags, placeholders (`{name}`, `%s`, `{{var}}`), and markup from accidental edits
- Warn about missing, extra, or reordered placeholders in translations
- Never touch what is not translatable

### ✍️ Comfortable translating
- Side-by-side source and target view
- Translation memory and glossary support *(planned)*
- Keyboard-friendly editing and quick navigation between items
- Clear status markers so you always know what is left

## Quick start

> ⚠️ Ferry is in early development. Interfaces and commands may change.

```bash
# Clone the repository
git clone https://github.com/<your-username>/ferry.git
cd ferry

# Install and run (replace with your stack's actual commands)
<install command>
<run command>
```

### Your first crossing

1. **New project**: choose your source file (for example, `strings.xml`) and its language.
2. **Add languages**: pick targets such as Persian, Arabic, or German.
3. **Translate**: open a language and work through the items.
4. **Export**: write the translated files back in the original format.

## Concepts

| Term | Meaning |
|------|---------|
| **Project** | The whole journey: one source language plus its target languages |
| **Port** | A language in the project, the source or any target |
| **Cargo** | A translatable item: a string, a cell, a subtitle line |
| **Crossing** | The translation progress of one language |
| **Manifest** | The project file describing sources, languages, and settings |

## Roadmap

- [ ] Core project model (source language, targets, items)
- [ ] Import/export: TXT, XML, CSV, JSON, SRT
- [ ] Progress tracking per language and per item
- [ ] Direction and bidi tools
- [ ] Number and digit system tools
- [ ] Locale-aware checks (plurals, dates, separators)
- [ ] Placeholder and markup protection
- [ ] Glossary and translation memory
- [ ] More formats (PO, XLIFF, YAML, RESX, and others)
- [ ] Plugin system for custom formats and checks

Have an idea? Open an issue and tell us.

## Contributing

Contributions are very welcome, whether code, documentation, new format support, or
reports about how a specific script or language behaves. Native speakers' feedback on
RTL, shaping, and locale issues is especially valuable.

1. Fork the repository
2. Create a branch: `git checkout -b feature/my-idea`
3. Commit your changes and open a pull request

Please see `CONTRIBUTING.md` for guidelines.

## License

Released under the [MIT License](LICENSE).

---

<p align="center"><em>Every language is a shore. Ferry is how your words get across.</em></p>

<p align="center"><em>This README is made by Claude AI. Report mistakes through issues.</em></p>
