CREATE TABLE `SpellLists` (
        `id`	INTEGER,
        `uri`	TEXT NOT NULL UNIQUE,
        PRIMARY KEY(id)
)

CREATE TABLE `SpellListMembers` (
        `id`	INTEGER,
        `spellList`	INTEGER NOT NULL,
        `level` INTEGER NOT NULL,
        `spellId` INTEGER NOT NULL,
        PRIMARY KEY(id),
        FOREIGN KEY(`spellList`) REFERENCES SpellLists
);
