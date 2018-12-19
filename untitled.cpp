class Ligne {
private:
	Entity m_caseDeLeft, m_caseDumiddle, m_caseDeRight;
public:
	entityAt(Position position) {
		switch (position) {
			case Position::LEFT:
				return m_caseDeLeft;

			case Position::MIDDLE:
				return m_caseDumiddle;

			case Position::RIGHT:
				return m_caseDeRight;
		}
	}

	Linge(Entity caseDeLeft, Entity caseDumiddle, Entity caseDeRight) :  m_caseDeLeft(caseDeLeft), m_caseDumiddle(caseDumiddle), m_caseDeRight(caseDeRight) {}

	~Ligne() {}
}



int main(void) {

	for each ligneafaire {

		pointeurQueue->push_back(Ligne(Entity(), Jump(), Crouch());
	}

}



queue<Ligne>

entité = grille.first().entityAt(Player.position());

enité.action(Player);