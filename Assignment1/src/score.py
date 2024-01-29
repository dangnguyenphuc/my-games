class ScoreManager:
    def __init__(self, score=0, miss=0):
        self.score = 0
        self.miss = 0

    def increase_score(self, points=1):
        self.score += points

    def reset_score(self):
        self.score = 0

    def decrease_score(self, points=1):
        self.score -= points

    def increase_miss(self, points=1):
        self.miss += points

    def reset_miss(self):
        self.miss = 0

    def decrease_miss(self, points=1):
        self.miss -= points

    def scoreEvaluation(self, maxPoint):
        if self.score < maxPoint/3:
            return 0

        if self.score < maxPoint/2:
            return 1

        if self.score < maxPoint*2/3:
            return 2

        return 3