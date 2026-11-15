import { Copy } from 'lucide-react';

export default function ProblemCard() {
  return (
    <section className="panel problem">
      <span className="chip">Խնդիր՝</span>
      <strong>lim x→0 (√(1+x) − √(1−x)) / x</strong>
      <span className="chip">Սահման</span>
      <span className="icon-btn"><Copy size={16} /></span>
    </section>
  );
}