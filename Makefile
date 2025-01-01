clean:
	rm ~/.cache/Qomodoro/pomodoro.db
db-fill:
	sqlite3 ~/.cache/Qomodoro/pomodoro.db < db.sql
