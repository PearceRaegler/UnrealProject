// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"

void UScoreWidget::AddToScore(int32 amount) {
	score += amount;

	ScoreText->SetText( FText::FromString( TEXT( "Score: {0}", score ) ) );
}

