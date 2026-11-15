const steps = [
    ['Analyze the problem', 'Direct substitution gives 0/0, so we need another method.'],
    ['Choose the method', 'Recommended: Rationalization.'],
    ['Solve', 'Multiply by the conjugate.'],
    ['Take the limit', '2 / (1 + 1) = 1'],
    ['Result', 'The limit equals 1.'],
  ];
  
  export default function StepsPanel() {
    return (
      <aside className="panel steps">
        <h2>Solution Steps</h2>
        {steps.map(([title, text], i) => (
          <div key={title} className="step">
            <span className="num">{i + 1}</span>
            <div>
              <h3>{title}</h3>
              <p>{text}</p>
            </div>
          </div>
        ))}
        <div className="actions">
          <button className="btn primary">Show another method</button>
          <button className="btn">View explanation</button>
        </div>
      </aside>
    );
  }