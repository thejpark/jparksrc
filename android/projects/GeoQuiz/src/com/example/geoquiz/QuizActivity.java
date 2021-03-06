package com.example.geoquiz;

import android.app.Activity;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import android.util.Log;
import android.app.ActionBar;
import android.annotation.TargetApi;

public class QuizActivity extends Activity {

    Button mTrueButton;
    Button mFalseButton;
    Button mNextButton;
    Button mCheatButton;
    boolean mIsCheater;
    TextView mQuestionTextView;
    private static final String TAG = "QuizActivity";
    private static final String KEY_INDEX = "index";

    TrueFalse[] mAnswerKey = new TrueFalse[] {
            new TrueFalse(R.string.question_oceans, true),
            new TrueFalse(R.string.question_mideast, false),
            new TrueFalse(R.string.question_africa, false),
            new TrueFalse(R.string.question_americas, true),
            new TrueFalse(R.string.question_asia, true)
    };
    private int mCurrentIndex;

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        mIsCheater = data.getBooleanExtra(CheatActivity.EXTRA_ANSWER_SHOWN, false);
    }

    @Override
    public void onSaveInstanceState(Bundle savedInstanceState) {
        super.onSaveInstanceState(savedInstanceState);
        Log.i(TAG, "onSaveInstanceState");
        savedInstanceState.putInt(KEY_INDEX, mCurrentIndex);
    }

    @Override
    public void onStart() {
	super.onStart();
	Log.d(TAG, "onStart() called");
    }

    @Override
    public void onPause() {
	super.onPause();
	Log.d(TAG, "onPause() called");
    }

    @Override
    public void onStop() {
	super.onStop();
	Log.d(TAG, "onStop() called");
    }

    @Override
    public void onResume() {
	super.onResume();
	Log.d(TAG, "onResume() called");
    }

    @Override
    public void onDestroy() {
	super.onDestroy();
	Log.d(TAG, "onDestroy() called");
    }
    
    // the below TargetApi tells Lint to ignore errors related SDK version
    @TargetApi(19)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
	Log.d(TAG, "onCreate(Bundle) called");
        setContentView(R.layout.activity_quiz);

	// SDK version dependent code
	if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB)
	{
	    Log.d(TAG, "SDK is higher than honeycomb");
	    // the Andrloid Lint will complain if the target API does not have
	    // methods used in this block. The above TargetApi annotation
	    // supressess the lint error
	    ActionBar actionBar = getActionBar();
	    actionBar.setSubtitle("Bodies of water");
	}

        mQuestionTextView = (TextView)findViewById(R.id.question_text_view);
	int question = mAnswerKey[mCurrentIndex].getQuestion();
	mQuestionTextView.setText(question);

        mIsCheater = false;

        mTrueButton = (Button)findViewById(R.id.true_button);
        mTrueButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
		//  we should not use 'this', as this means the object of the anonymous class
		checkAnswer(true);
            }
        });

        mFalseButton = (Button)findViewById(R.id.false_button);		
        mFalseButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
		checkAnswer(false);
            }
        });

        mNextButton = (Button)findViewById(R.id.next_button);
        mNextButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mCurrentIndex = (mCurrentIndex + 1) % mAnswerKey.length; 
                mIsCheater = false;
                updateQuestion();
            }
        });

        mCheatButton = (Button)findViewById(R.id.cheat_button);
        mCheatButton.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                Log.d(TAG, "cheat button clicked");
                Intent i = new Intent(QuizActivity.this, CheatActivity.class);
                Log.d(TAG, "intent created");
                boolean answerIsTrue = mAnswerKey[mCurrentIndex].isTrueQuestion();
                i.putExtra(CheatActivity.EXTRA_ANSWER_IS_TRUE, answerIsTrue);
                startActivityForResult(i, 0);
            }
        });

        if (savedInstanceState != null) {
            mCurrentIndex = savedInstanceState.getInt(KEY_INDEX, 0);
        }

	updateQuestion();
    }

    private void updateQuestion() {
        int question = mAnswerKey[mCurrentIndex].getQuestion();
        mQuestionTextView.setText(question);
    }

    private void checkAnswer(boolean userPressedTrue) {
        boolean answerIsTrue = mAnswerKey[mCurrentIndex].isTrueQuestion();
        
        int messageResId = 0;

        if (mIsCheater) {
	    if (userPressedTrue == answerIsTrue) {
                messageResId = R.string.judgment_toast;
            } else {
                messageResId = R.string.incorrect_judgement_toast;
            }
	} else {
	    if (userPressedTrue == answerIsTrue) {
		messageResId = R.string.correct_toast;
	    } else {
		messageResId = R.string.incorrect_toast;
	    }
	}
        Toast.makeText(this, messageResId, Toast.LENGTH_SHORT)
            .show();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.activity_quiz, menu);
        return true;
    }

}
