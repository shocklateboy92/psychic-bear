
CREATE TABLE "Modifiers" (
	`id`	INTEGER NOT NULL,
	`Attribute`	INTEGER NOT NULL,
	`Name`	TEXT,
	`Amount`	INTEGER,
	`TimeStamp`	DATETIME DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY(id ASC),
	FOREIGN KEY(`Attribute`) REFERENCES Attributes ( id )
);

CREATE TABLE "Attributes" (
	`Uri`	TEXT NOT NULL,
	`id`	INTEGER,
    PRIMARY KEY(id ASC)
);
