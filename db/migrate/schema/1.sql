
CREATE TABLE "BonusSources" (
    `uri`		TEXT NOT NULL UNIQUE,
    `active`	BOOLEAN DEFAULT '0',
    `id`		INTEGER,
    PRIMARY KEY(id)
);
